cd database
mongod --dbpath . &
cd ..

cd web-server
node app &
cd ..

cd work-server
node app &
cd ..
