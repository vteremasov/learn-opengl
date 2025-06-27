set -e

cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -S . -B build
ln -s build/compile_commands.json .

echo "Done..."
