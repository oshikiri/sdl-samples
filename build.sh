project=clock

pushd ${project}/
make
mkdir ../docs/${project}/
cp index.* ../docs/${project}/
popd
