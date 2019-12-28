open ReactNative;
open ReactNavigation;

module GetGameSquares = [%graphql
  {|
    query getGameSquares($id: ID!) {
        getGameSquares(id: $id) {
            _id
            x
            y
            isTaken
            takenByUser {
              _id
              first_name
            }
        }
    }
  |}
];

module GetGameSquareQuery = ReasonApollo.CreateQuery(GetGameSquares);

[@react.component]
let make = (~navigation: ReactNavigation.Navigation.t) => {
  let gameId = navigation->Navigation.getParam("gameId");

  <View>
    <TouchableOpacity
      onPress={_e => navigation->Navigation.navigate("Games")}>
      <Text>
        {switch (gameId->Js.Nullable.toOption) {
         | None => "Error getting Game Id"->React.string
         | Some(gameId) => gameId->React.string
         }}
      </Text>
    </TouchableOpacity>
  </View>;
};

make->NavigationOptions.setDynamicNavigationOptions(_params => {
  // let navigation = params##navigation;
  // let navigationOptions = params##navigationOptions;
  // let screenProps = params##screenProps;
  /* More properties can be set dynamically based on navigation, navigationOptions or screenProps. */
  NavigationOptions.t(
    ~title="Game",
    ~headerTintColor="red",
    (),
  )
});