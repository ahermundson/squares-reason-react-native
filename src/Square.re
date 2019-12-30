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
let make = (~square: square, _children) =>
  <MarkSquareMutation>
    ...{(mutation, _) => {
      let updatedSquare = MarkSquare.make(~id=square##_id, ());
      square##isTaken
        ? switch (square##takenByUser) {
          | None => <View> <Text> "Taken"->React.string </Text> </View>
          | Some(user) =>
            <View> <Text> {user##first_name->React.string} </Text> </View>
          }
        : <TouchableOpacity
            onPress={_mouseEvent =>
              mutation(~variables=updatedSquare##variables, ()) |> ignore
            }>
            <View key={string_of_int(square##x)}>
              <Text>
                {{
                   "X " ++ string_of_int(square##x);
                 }
                 ->React.string}
              </Text>
              <Text>
                {{
                   "Y " ++ string_of_int(square##y);
                 }
                 ->React.string}
              </Text>
            </View>
          </TouchableOpacity>;
    }}
  </MarkSquareMutation>;