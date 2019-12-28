open ReactNative;
open ReactNavigation;

module GetAllGames = [%graphql
  {|
    query getAllGames {
        allGames {
            _id
            boardId
            homeTeam {
              teamName
            }
        }
    }
  |}
];

module GetAllGamesQuery = ReasonApollo.CreateQuery(GetAllGames);

[@react.component]
let make = (~navigation: ReactNavigation.Navigation.t) => {
  <GetAllGamesQuery>
    ...{({result}) =>
      switch (result) {
      | Loading => <Text> "Loading"->React.string </Text>
      | Error(_error) => <Text> "Error"->React.string </Text>
      | Data(response) =>
        switch (response##allGames) {
        | None => <Text> "No games currently"->React.string </Text>
        | Some(games) =>
          games
          |> Js.Array.map(game =>
               <TouchableOpacity
                 key={game##_id}
                 onPress={_e =>
                   navigation->Navigation.navigateWithParams(
                     "Game",
                     {"gameId": game##boardId},
                   )
                 }>
                 <Text> {React.string(game##_id)} </Text>
               </TouchableOpacity>
             )
          |> ReasonReact.array
        }
      }
    }
  </GetAllGamesQuery>;
};

make->NavigationOptions.setDynamicNavigationOptions(params => {
  let navigation = params##navigation;
  let navigationOptions = params##navigationOptions;
  let screenProps = params##screenProps;

  /* More properties can be set dynamically based on navigation, navigationOptions or screenProps. */
  NavigationOptions.t(~title="Games", ~headerTintColor="red", ());
});