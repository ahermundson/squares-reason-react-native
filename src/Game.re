open ReactNative;
open ReactNavigation;
open SharedTypes;
open ApolloHooks;

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
            board {
              _id
            }
        }
    }
  |}
];

module GetGameSquareQuery = ReasonApollo.CreateQuery(GetGameSquares);

module SquareSubscription = [%graphql
  {|
    subscription($id: ID!) {
      squareTaken(id: $id) {
        _id
        x
        y
        isTaken
        takenByUser{
          _id
          first_name
        }
        board {
          _id
        }
      }
    }
  |}
];

module SquareSub = ReasonApollo.CreateSubscription(SquareSubscription);

let createBoardRow = (squares, x) =>
  squares |> Js.Array.filter(square => square##x == x);

let parseSquares = squares => [|
  createBoardRow(squares, 0),
  createBoardRow(squares, 1),
  createBoardRow(squares, 2),
  createBoardRow(squares, 3),
  createBoardRow(squares, 4),
  createBoardRow(squares, 5),
  createBoardRow(squares, 6),
  createBoardRow(squares, 7),
  createBoardRow(squares, 8),
  createBoardRow(squares, 9),
|];

[@react.component]
let make = (~navigation: ReactNavigation.Navigation.t) => {
  let gameId = navigation->Navigation.getParam("gameId");
  let teams = navigation->Navigation.getParam("teams");

  let (squares, setSquares) =
    React.useState(() => {
      let squareArray: array(square) = [||];
      squareArray;
    });

  let findSquare = (square, squares) => {
    Js.log(squares);
    switch (squares) {
    | None => Js.log("no squares")
    | Some(sq) =>
      let squareToUpdate =
        sq |> Js.Array.findIndex(s => s##_id == square##_id);
      Js.log(squareToUpdate);
      Js.log(sq[squareToUpdate]);
      if (!sq[squareToUpdate]##isTaken) {
        sq[squareToUpdate] = square;
        setSquares(_ => sq);
      };
    };
  };

  <ScrollView>
    <Text style=Style.(style(~textAlign=`center, ()))>
      {switch (teams->Js.Nullable.toOption) {
       | None => ""->React.string
       | Some(teams) => teams->React.string
       }}
    </Text>
    <View style=Style.(style(~flexDirection=`row, ()))>
      {switch (gameId->Js.Nullable.toOption) {
       | None => "Error getting Game Id"->React.string
       | Some(gameId) =>
         let gameQuery = GetGameSquares.make(~id=gameId, ());
         let (simple, _full) =
           useQuery(
             GetGameSquares.definition,
             ~variables=GetGameSquares.makeVariables(~id=gameId, ()),
           );
         switch (simple) {
         | Loading => <Text> "Loading Squares"->React.string </Text>
         | NoData => <Text> "No Squares"->React.string </Text>
         | Error(_error) =>
           navigation->Navigation.navigate("Games");
           <Text> "Error"->React.string </Text>;
         | Data(response) =>
           let gameSquares = response##getGameSquares;
           switch (gameSquares) {
           | None => setSquares(_ => [||])
           | Some(z) =>
             if (Js.Array.length(squares) == 0) {
               setSquares(_ => z);
               Js.log("something");
             } else {
               Js.log("Something else");
             }
           };
           let parsedRows = parseSquares(squares);
           <SquareSub variables=gameQuery##variables>
             {(
                ({data}) => {
                  Js.log(data);
                  Js.log(parsedRows);
                  switch (data) {
                  | None => Js.log("Nothing here")
                  | Some(square) =>
                    findSquare(square##squareTaken, gameSquares)
                  };
                  parsedRows
                  |> Js.Array.mapi((row, i) =>
                       <BoardRow key={string_of_int(i)} row />
                     )
                  |> ReasonReact.array;
                }
              )}
           </SquareSub>;
         };
       }}
    </View>
  </ScrollView>;
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