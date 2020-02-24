import { ApolloLink } from "apollo-link";

const afterLink = new ApolloLink((operation, forward) =>
  forward(operation).map(response => {
    const context = operation.getContext();
    console.log("MAYBE?");
    const {
      response: { headers }
    } = context;

    console.log(headers);

    return response;
  })
);

export default afterLink;
