open ReactNavigation;

let routes = {
  "Login": Login.make,
  "Games": Games.make,
  "Game": Game.make,
  "Register": Register.make,
};

let navigator = StackNavigator.make(routes);

navigator->NavigationOptions.setNavigationOptions(
  NavigationOptions.t(~gesturesEnabled=false, ()),
);