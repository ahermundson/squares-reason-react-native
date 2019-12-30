type user = {
  .
  "_id": string,
  "first_name": string,
};
type square = {
  .
  "_id": string,
  "isTaken": bool,
  "x": int,
  "y": int,
  "takenByUser": option(user),
};