open ReactNative;
open SharedTypes;

[@react.component]
let make = (~row) =>
  <View style=Style.(style(~flexDirection=`row, ~justifyContent=`center, ()))>
    {row
     |> Js.Array.map((square: square) =>
          <View
            key={square##_id}
            style=Style.(
              style(
                ~flexDirection=`row,
                ~justifyContent=`center,
                ~borderWidth=1.,
                ~borderColor="pink",
                ~height=10.->dp,
                ~width=10.->dp,
                (),
              )
            )
          />
        )
     |> ReasonReact.array}
  </View>;