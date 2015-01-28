mkdir database
pushd . & cd database & start mongod --dbpath . & popd
pushd . & start node ./bin/www & popd