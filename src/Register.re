open ReactNative;

open ReactNavigation;
open ApolloHooks;

module Register = [%graphql
  {|
  mutation register($email: String!, $password: String!, $username: String!) {
      register(email: $email, password: $password, username: $username) {
          ok
          user {
            _id
          }
      }
  }
|}
];

type register = {
  .
  "register": {
    .
    "ok": bool,
    "user": option({. "_id": string}),
  },
};

[@react.component]
let make = (~navigation: ReactNavigation.Navigation.t) => {
  let (email, setEmail) = React.useState(() => "");
  let (password, setPassword) = React.useState(() => "");
  let (username, setUsername) = React.useState(() => "");
  let (loginMutation, _simple, _full) = useMutation(Register.definition);
  let (loginError, setLoginError) = React.useState(() => false);

  let register = () =>
    loginMutation(
      ~variables=Register.makeVariables(~email, ~password, ~username, ()),
      (),
    )
    |> Js.Promise.then_((response: Mutation.result(register)) => {
         switch (response) {
         | Data(data) =>
           data##register##ok
             ? {
               Js.log("ok");
               navigation->Navigation.navigate("Games");
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
      placeholder="email"
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
      value=username
      placeholder="Username"
      onChangeText={e => setUsername(_ => e)}
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
    <Button onPress={_ => register()} title="Submit" />
  </View>;
};

make->NavigationOptions.setDynamicNavigationOptions(_params => {
  // let navigation = params##navigation;
  // let navigationOptions = params##navigationOptions;
  // let screenProps = params##screenProps;
  /* More properties can be set dynamically based on navigation, navigationOptions or screenProps. */
  NavigationOptions.t(
    ~title="Register",
    ~headerTintColor="#01C357",
    (),
  )
});