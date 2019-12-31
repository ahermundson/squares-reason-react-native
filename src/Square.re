open ReactNative;
open SharedTypes;

module MarkSquare = [%graphql
  {|
  mutation markSquare($id: ID!) {
      markSquare(id: $id) {
          isTaken
      }
  }
|}
];

module MarkSquareMutation = ReasonApollo.CreateMutation(MarkSquare);
[@react.component]
let make = (~square: square) =>
  <MarkSquareMutation>
    ...{(mutation, _) => {
      let updatedSquare = MarkSquare.make(~id=square##_id, ());
      square##isTaken
        ? switch (square##takenByUser) {
          | None =>
            <View
              style=Style.(
                style(
                  ~borderColor="black",
                  ~borderWidth=1.,
                  ~justifyContent=`center,
                  ~alignItems=`center,
                  (),
                )
              )>
              <Text style=Style.(style(~color="black", ()))>
                {React.string("Taken")}
              </Text>
            </View>
          | Some(user) =>
            <View
              style=Style.(
                style(
                  ~borderColor="black",
                  ~borderWidth=1.,
                  ~justifyContent=`center,
                  ~alignItems=`center,
                  ~minHeight=55.->dp,
                  (),
                )
              )>
              <View>
                <Text style=Style.(style(~fontSize=22., ()))>
                  {user##first_name->React.string}
                </Text>
              </View>
            </View>
          }
        : <TouchableOpacity
            onPress={_mouseEvent =>
              mutation(~variables=updatedSquare##variables, ()) |> ignore
            }>
            <View
              style=Style.(
                style(
                  ~borderColor="black",
                  ~borderWidth=1.,
                  ~justifyContent=`center,
                  ~alignItems=`center,
                  (),
                )
              )
              key={string_of_int(square##x)}>
              <Text style=Style.(style(~color="black", ~fontSize=22., ()))>
                {{
                   "X" ++ string_of_int(square##x);
                 }
                 ->React.string}
              </Text>
              <Text style=Style.(style(~color="black", ~fontSize=22., ()))>
                {{
                   "Y" ++ string_of_int(square##y);
                 }
                 ->React.string}
              </Text>
            </View>
          </TouchableOpacity>;
    }}
  </MarkSquareMutation>;