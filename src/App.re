open ReactNavigation;

module MyAppContainer =
  AppContainer.Make({
    type screenProps = {. "someProp": int};
    let navigator = MyStackNavigator.navigator;
  });

[@react.component]
let make = () => {
  let screenProps = {"someProp": 42};
  let inMemoryCache = ApolloInMemoryCache.createInMemoryCache();

  let httpLink =
    ApolloLinks.createHttpLink(~uri="http://localhost:4000/graphql", ());

  let wsLink =
    ApolloLinks.webSocketLink(~uri="ws://localhost:4000/graphql", ());

  let instance =
    ReasonApollo.createApolloClient(~link=wsLink, ~cache=inMemoryCache, ());
  <ReasonApollo.Provider client=instance>
    <MyAppContainer screenProps />
  </ReasonApollo.Provider>;
};