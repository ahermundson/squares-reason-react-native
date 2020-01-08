[@bs.module "react-native-svg"]
external make: (~height: int) => React.element = "default";

[@bs.deriving abstract]
type props = {
  [@bs.optional]
  height: int,
};
[@react.component]
let make = (~height) => make(~height);