open ReactNative;

type reactNativeNewAppScreenColors = {
  .
  "primary": string,
  "white": string,
  "lighter": string,
  "light": string,
  "black": string,
  "dark": string,
};

[@bs.module "react-native/Libraries/NewAppScreen"]
external colors: reactNativeNewAppScreenColors = "Colors";
let styles =
  Style.(
    StyleSheet.create({
      "scrollView":
        style(~backgroundColor=colors##lighter, ~height=100.->dp, ()),
      "engine": style(~position=`absolute, ~right=0.->dp, ()),
      "body": style(~backgroundColor=colors##white, ()),
      "sectionContainer":
        style(~marginTop=32.->dp, ~paddingHorizontal=24.->dp, ()),
      "sectionTitle":
        style(~fontSize=24., ~fontWeight=`_600, ~color=colors##black, ()),
      "sectionDescription":
        style(
          ~marginTop=8.->dp,
          ~fontSize=18.,
          ~fontWeight=`_400,
          ~color=colors##dark,
          (),
        ),
      "highlight": style(~fontWeight=`_700, ()),
      "footer":
        style(
          ~color=colors##dark,
          ~fontSize=12.,
          ~fontWeight=`_600,
          ~padding=4.->dp,
          ~paddingRight=12.->dp,
          ~textAlign=`right,
          (),
        ),
    })
  );

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
let make = () =>
  <>
    <ReasonApollo.Provider client=Client.instance>
      <SafeAreaView>
        <ScrollView style={styles##scrollView}>
          <GetAllGamesQuery>
            ...{({result}) =>
              switch (result) {
              | Loading => <Text> "Loading"->React.string </Text>
              | Error(_error) => <Text> "Error"->React.string </Text>
              | Data(response) =>
                switch (response##allGames) {
                | None => <Text> "No games"->React.string </Text>
                | Some(games) =>
                  games
                  |> Js.Array.map(game =>
                       <Text key={game##boardId}>
                         {game##boardId->React.string}
                       </Text>
                     )
                  |> ReasonReact.array
                }
              }
            }
          </GetAllGamesQuery>
        </ScrollView>
      </SafeAreaView>
    </ReasonApollo.Provider>
  </>;