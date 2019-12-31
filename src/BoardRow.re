open ReactNative;
open SharedTypes;

[@react.component]
let make = (~row) =>
  <ScrollView style=Style.(style(~flexDirection=`row, ()))>
    {row
     |> Js.Array.map((square: square) => <Square key={square##_id} square />)
     |> ReasonReact.array}
  </ScrollView>;