mkdir database
pushd . & cd database & start mongod --dbpath . & popd
pushd . & start npm start & popd

