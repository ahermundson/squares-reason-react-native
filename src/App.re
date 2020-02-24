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

[@bs.module "./afterLink"]
external afterLink: ReasonApolloTypes.apolloLink = "default";

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

  let authLink =
    ApolloLinks.createContextLinkPromise(() => {
      let%Async token = AsyncStorage.getItem("token");
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

  let links = ApolloLinks.from([|authLink, afterLink, link|]);

  let instance =
    ReasonApollo.createApolloClient(~link=links, ~cache=inMemoryCache, ());

  <ReasonApollo.Provider client=instance>
    <ApolloHooks.Provider client=instance>
      <MyAppContainer screenProps />
    </ApolloHooks.Provider>
  </ReasonApollo.Provider>;
};