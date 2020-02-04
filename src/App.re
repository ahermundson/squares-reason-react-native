open ReactNavigation;
open ReactNative;
[@bs.send]
external concat:
  (ReasonApolloTypes.apolloLink, ReasonApolloTypes.apolloLink) =>
  ReasonApolloTypes.apolloLink =
  "concat";

module MyAppContainer =
  AppContainer.Make({
    type screenProps = {. "someProp": int};
    let navigator = MyStackNavigator.navigator;
  });

module Async = {
  let let_ = (prom, cb) => Js.Promise.then_(cb, prom);
};

[@react.component]
let make = () => {
  let screenProps = {"someProp": 42};
  let inMemoryCache = ApolloInMemoryCache.createInMemoryCache();

  let httpLink =
    ApolloLinks.createHttpLink(~uri="http://localhost:4000/graphql", ());

  let wsLink =
    ApolloLinks.webSocketLink(
      ~uri="ws://localhost:4000/graphql",
      ~reconnect=true,
      (),
    );
  let getToken = () => {
    let%Async token = AsyncStorage.getItem("token");
    Js.log(token);
    Js.Promise.resolve(token);
  };

  let authLink =
    ApolloLinks.createContextLink(() => {
      let%Async token = AsyncStorage.getItem("token");
      // {
      //   "headers": {
      //     "authorization": "",
      //   },
      // }
      Js.Promise.resolve({
        "headers": {
          "authorization": token,
        },
      });
    });

  let link =
    ApolloLinks.split(
      operation => {
        let operationDefition =
          ApolloUtilities.getMainDefinition(operation##query);
        operationDefition##kind == "OperationDefinition"
        &&
        operationDefition##operation == "subscription";
      },
      wsLink,
      httpLink,
    );

  let linkWithAuth = authLink->(concat(link));

  let instance =
    ReasonApollo.createApolloClient(
      ~link=linkWithAuth,
      ~cache=inMemoryCache,
      (),
    );

  <ReasonApollo.Provider client=instance>
    <ApolloHooks.Provider client=instance>
      <MyAppContainer screenProps />
    </ApolloHooks.Provider>
  </ReasonApollo.Provider>;
};