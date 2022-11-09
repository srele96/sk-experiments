# Layers Design Document

```txt
get_size():
  // divide the width of the window by a value larger than multiplier
  // because all my moving logic bases on width of the layer
  layer_width = screen_width / 4
  container_width: 1.6 * layer_width
  container_height: 1.5 * layer_width
  return { layer_width, container_width, container_height }

space_layers_equally: {
  [-6]: { move:  -95%, scale: .3, depth: 1, move_top_layer: 60% }
  [-5]: { move:  -80%, scale: .4, depth: 2, move_top_layer: 50% }
  [-4]: { move:  -65%, scale: .5, depth: 3, move_top_layer: 40% }
  [-3]: { move:  -50%, scale: .6, depth: 4, move_top_layer: 30% }
  [-2]: { move:  -35%, scale: .7, depth: 5, move_top_layer: 20% }
  [-1]: { move:  -20%, scale: .8, depth: 6, move_top_layer: 10% }
  [ 0]: { move:    0,  scale:  1, depth: 7, move_top_layer:  0% }
  [ 1]: { move:   20%, scale: .8, depth: 6 }
  [ 2]: { move:   35%, scale: .7, depth: 5 }
  [ 3]: { move:   50%, scale: .6, depth: 4 }
  [ 4]: { move:   65%, scale: .5, depth: 3 }
  [ 5]: { move:   80%, scale: .4, depth: 2 }
  [ 6]: { move:   95%, scale: .3, depth: 1 }
}

space_around_top_layer: {
  [-6]: { move: -175%, scale: .3, depth: 1, move_top_layer: 140% }
  [-5]: { move: -160%, scale: .4, depth: 2, move_top_layer: 130% }
  [-4]: { move: -145%, scale: .5, depth: 3, move_top_layer: 120% }
  [-3]: { move: -130%, scale: .6, depth: 4, move_top_layer: 110% }
  [-2]: { move: -115%, scale: .7, depth: 5, move_top_layer: 100% }
  [-1]: { move: -100%, scale: .8, depth: 6, move_top_layer:  90% }
  [ 0]: { move:    0 , scale:  1, depth: 7, move_top_layer:   0% }
  [ 1]: { move:  100%, scale: .8, depth: 6 }
  [ 2]: { move:  115%, scale: .7, depth: 5 }
  [ 3]: { move:  130%, scale: .6, depth: 4 }
  [ 4]: { move:  145%, scale: .5, depth: 3 }
  [ 5]: { move:  160%, scale: .4, depth: 2 }
  [ 6]: { move:  175%, scale: .3, depth: 1 }
}

properties(mirror_properties):
  this.mirror_properties = mirror_properties

  this.get_arranged_mirror_properties(index):
    begin = 0
    length = 7
    result = Array(length)
    current_property = begin - index

    for i = begin to length
      result = mirror_properties[current_property]

    return result

  this.get_merged_properties(index):
    mirror_properties = this.get_arranged_mirror_properties(index)
    additional_properties = [
      { src, alt },
      { src, alt },
      { src, alt },
      { src, alt },
      { src, alt },
      { src, alt },
      { src, alt },
    ]

    result = Array(length)

    for i = begin to length
      result[i] = { ...mirror_properties[i], ...additional_properties[i] }

    return result
```
