module Svg = {
  [@bs.module "react-native-svg"] [@react.component]
  external make:
    (
      ~height: string,
      ~width: string,
      ~viewBox: string,
      ~children: ReasonReact.reactElement
    ) =>
    React.element =
    "Svg";
  let make = make;
};

module G = {
  [@bs.module "react-native-svg"] [@react.component]
  external make:
    (
      ~id: string,
      ~dataName: string=?,
      ~transform: string=?,
      ~fill: string=?,
      ~stroke: string=?,
      ~strokeWidth: string=?,
      ~children: ReasonReact.reactElement=?
    ) =>
    React.element =
    "G";
  let make = make;
};

module Circle = {
  [@bs.module "react-native-svg"] [@react.component]
  external make:
    (
      ~cx: string,
      ~cy: string,
      ~r: string,
      ~stroke: string=?,
      ~fill: string=?
    ) =>
    React.element =
    "Circle";
  let make = make;
};

module Path = {
  [@bs.module "react-native-svg"] [@react.component]
  external make:
    (
      ~id: string,
      ~dataName: string=?,
      ~d: string=?,
      ~transform: string=?,
      ~fill: string=?
    ) =>
    React.element =
    "Path";
};