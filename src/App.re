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

  let instance =
    ReasonApollo.createApolloClient(~link=httpLink, ~cache=inMemoryCache, ());
  <ReasonApollo.Provider client=instance>
    <MyAppContainer screenProps />
  </ReasonApollo.Provider>;
};