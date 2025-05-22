import subprocess

command = [
    "python",
    "C:\\Users\\enzo\\OneDrive\\Documentos\\CircularDependency\\dependency_graph.py",
    "-f", "jpg",
    "C:\\Users\\enzo\\OneDrive\\Documentos\\PlatformIO\\Projects\\AraraPlaca\\lib\\EasySTEAM",
    "C:\\Users\\enzo\\OneDrive\\Documentos\\CircularDependency\\out.jpg"
]

subprocess.run(command)