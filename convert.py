from cairosvg import svg2png
import os

svg_files = [ fil.split('.')[0] for fil in os.listdir('assets') 
  if os.path.isfile(f'assets/{fil}') and '.svg' in fil]


for fil in svg_files:
  print(f'[INFO] Converting {fil}')
  svg2png(url=f"assets/{fil}.svg", write_to=f"assets/{fil}.png", 
    parent_width=100, parent_height=200, scale=0.5)

