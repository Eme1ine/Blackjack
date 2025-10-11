import os
import hpp2plantuml
from pathlib import Path

current_dir = str(Path(__file__).resolve().parent)
l = []
for root, dirs, files in os.walk(current_dir + "\\..\\"):
    for f in files:
        if f.endswith(".hpp"):
            s = os.path.join(root, f)
            print(s)
            l.append(s)

hpp2plantuml.CreatePlantUMLFile(l, current_dir + "\\classes.puml")
