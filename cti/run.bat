pushd . & cd database & start mongod --dbpath . & popd
pushd . & cd donjin-server & start node app & popd
pushd . & cd work-server & start npm start & popd
pushd . & cd rc-web-server & start npm start & popd
