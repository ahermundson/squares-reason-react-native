open ReactNative;
open ApolloHooks;
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

[@react.component]
let make = (~square: square) => {
  let springValue = React.useRef(Animated.Value.create(0.3));
  let spring = () => {
    Animated.(
      timing(
        springValue->React.Ref.current,
        Value.Timing.config(
          ~toValue=1.->Value.Timing.fromRawValue,
          ~duration=150.,
          (),
        ),
      )
    )
    ->Animated.start();
  };
  React.useEffect1(
    () => {
      spring();
      None;
    },
    [|square##isTaken|],
  );
  let (screamMutation, _simple, _full) =
    useMutation(
      ~variables=MarkSquare.makeVariables(~id=square##_id, ()),
      MarkSquare.definition,
    );

  let scream = _ => {
    screamMutation()
    |> Js.Promise.then_(_result => {Js.Promise.resolve()})
    |> ignore;
  };
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
            <Animated.Text
              style=Style.(
                style(
                  ~fontSize=22.,
                  ~transform=[|
                    scale(
                      ~scale=
                        springValue
                        ->React.Ref.current
                        ->Animated.StyleProp.float,
                    ),
                  |],
                  (),
                )
              )>
              {user##first_name->React.string}
            </Animated.Text>
          </View>
        </View>
      }
    : <TouchableOpacity onPress={_pressEvent => scream()}>
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
};