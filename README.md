SO_tp_2

//crear el contenedor (2.0)
docker run -d -v ${PWD}:/root --privileged  -ti --name RowDaBoat-x64barebones-d4e1c147f975 agodio/itba-so:2.0

//compilo el projecto
./build.sh

//ejecuto el projecto
sudo ./run.sh

//elimino el contenedor (2.0)
docker rm -f RowDaBoat-x64barebones-d4e1c147f975

//crear el contenedor (1.0)
docker run -d -v ${PWD}:/root --privileged  -ti --name RowDaBoat-x64barebones-d4e1c147f975 agodio/itba-so:1.0

//compilo el projecto
./build.sh

//ejecuto el projecto
sudo ./run.sh

//inicializo el contenedor (1.0)
docker start RowDaBoat-x64barebones-d4e1c147f975

//compilo el projecto
./build.sh

//ejecuto el projecto
sudo ./run.sh