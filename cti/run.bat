pushd . & mkdir database & cd database & start mongod --dbpath . & popd
pushd . & cd web-server & start npm start & popd

