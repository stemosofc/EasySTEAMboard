from subprocess import run

command = [
    "python","CircularDependency\\dependency_graph.py",
    "-f", "jpg",
    "lib\\EasySTEAM",
    "CircularDependency\\out.jpg"
]

run(command)