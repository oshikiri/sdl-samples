projects=(
    clock
    simple_pendulum
)

for project in "${projects[@]}" ; do
    echo ">>> Building ${project}..."
    pushd ${project}/
    make
    mkdir -p ../docs/${project}/
    cp index.* ../docs/${project}/
    popd
done
