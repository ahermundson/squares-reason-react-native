open ReactNative;

open ReactNavigation;

[@react.component]
let make = (~navigation: ReactNavigation.Navigation.t) => {
  let (userName, setUsername) = React.useState(() => "");
  let (password, setPassword) = React.useState(() => "");
  <View>
    <TextInput
      style=Style.(
        style(
          ~borderWidth=1.,
          ~borderColor="black",
          ~marginHorizontal=35.->dp,
          ~paddingVertical=15.->dp,
          ~paddingLeft=10.->dp,
          ~marginTop=15.->dp,
          (),
        )
      )
      value=userName
      placeholder="Username"
      onChangeText={e => setUsername(_ => e)}
    />
    <TextInput
      style=Style.(
        style(
          ~borderWidth=1.,
          ~borderColor="black",
          ~marginHorizontal=35.->dp,
          ~paddingVertical=15.->dp,
          ~paddingLeft=10.->dp,
          ~marginTop=15.->dp,
          (),
        )
      )
      value=password
      placeholder="Password"
      onChangeText={e => setPassword(_ => e)}
      secureTextEntry=true
    />
    <Button onPress={_ => Js.log("pressed")} title="Submit" />
  </View>;
};

make->NavigationOptions.setDynamicNavigationOptions(_params => {
  // let navigation = params##navigation;
  // let navigationOptions = params##navigationOptions;
  // let screenProps = params##screenProps;
  /* More properties can be set dynamically based on navigation, navigationOptions or screenProps. */
  NavigationOptions.t(
    ~title="Login",
    ~headerTintColor="#01C357",
    (),
  )
});