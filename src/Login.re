open ReactNative;

open ReactNavigation;
open ApolloHooks;

module Login = [%graphql
  {|
  mutation login($email: String!, $password: String!) {
      login(email: $email, password: $password) {
          ok
          token
          refreshToken
          errors
      }
  }
|}
];

type login = {
  .
  "login": {
    .
    "ok": bool,
    "refreshToken": option(string),
    "token": option(string),
    "errors": option(string),
  },
};

[@react.component]
let make = (~navigation: ReactNavigation.Navigation.t) => {
  React.useEffect0(() => {
    AsyncStorage.getItem("token")
    |> Js.Promise.then_(stringOrNull => {
         Js.log2("CHECKING_AUTH_TOKEN", stringOrNull);
         Js.Promise.resolve();
       })
    |> ignore;
    None;
  });
  let (email, setEmail) = React.useState(() => "");
  let (password, setPassword) = React.useState(() => "");
  let (loginMutation, _simple, _full) = useMutation(Login.definition);
  let (loginError, setLoginError) = React.useState(() => false);

  let login = () =>
    loginMutation(~variables=Login.makeVariables(~email, ~password, ()), ())
    |> Js.Promise.then_((response: Mutation.result(login)) => {
         switch (response) {
         | Data(data) =>
           data##login##ok
             ? {
               switch (data##login##token) {
               | Some(token) =>
                 AsyncStorage.setItem("token", token) |> ignore;
                 navigation->Navigation.navigate("Games");

               | None => setLoginError(_ => true)
               };
             }
             : setLoginError(_ => true)
         | Error(e) =>
           setLoginError(_ => true);
           Js.Promise.resolve(Belt.Result.Error(`apolloErrors(e))) |> ignore;
         | NoData => Js.log("no data")
         };
         Js.Promise.resolve();
       })
    |> Js.Promise.catch(_ => {
         setLoginError(_ => true);
         Js.Promise.resolve();
       })
    |> ignore;
  <View>
    <TextInput
      style=Style.(
        style(
          ~borderWidth=1.,
          ~borderColor={
            loginError ? "red" : "black";
          },
          ~marginHorizontal=35.->dp,
          ~paddingVertical=15.->dp,
          ~paddingLeft=10.->dp,
          ~marginTop=15.->dp,
          (),
        )
      )
      value=email
      placeholder="Username"
      onChangeText={e => setEmail(_ => e)}
      autoCapitalize=`none
    />
    <TextInput
      style=Style.(
        style(
          ~borderWidth=1.,
          ~borderColor={
            loginError ? "red" : "black";
          },
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
    <Button onPress={_ => login()} title="Submit" />
    <Button
      onPress={_ => {
        Js.log("kjlfa;dksjf;");
        navigation->Navigation.navigate("Register");
      }}
      title="Register"
    />
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
}) /* navigation->Navigation.navigate("Games"*/;