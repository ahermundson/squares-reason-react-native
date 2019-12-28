open ReactNavigation;

let routes = {"Games": Games.make, "Game": Game.make};

let navigator = StackNavigator.make(routes);

navigator->NavigationOptions.setNavigationOptions(
  NavigationOptions.t(~gesturesEnabled=false, ()),
);