# Layers Design Document

```txt
get_mirror_properties(index):
  mirror_properties: {
    [-6]: { move: -95%, scale: .3, depth: 1 }
    [-5]: { move: -80%, scale: .4, depth: 2 }
    [-4]: { move: -65%, scale: .5, depth: 3 }
    [-3]: { move: -50%, scale: .6, depth: 4 }
    [-2]: { move: -35%, scale: .7, depth: 5 }
    [-1]: { move: -20%, scale: .8, depth: 6 }
    [ 0]: { move:   0%, scale:  1, depth: 7 }
    [ 1]: { move:  20%, scale: .8, depth: 6 }
    [ 2]: { move:  35%, scale: .7, depth: 5 }
    [ 3]: { move:  50%, scale: .6, depth: 4 }
    [ 4]: { move:  65%, scale: .5, depth: 3 }
    [ 5]: { move:  80%, scale: .4, depth: 2 }
    [ 6]: { move:  95%, scale: .3, depth: 1 }
  }

  begin = 0
  length = 7
  result = Array(length)
  current_property = begin - index

  for i = begin to length
    result = mirror_properties[current_property]

  return result

get_merged_properties(index)
  mirror_properties = get_mirror_properties(index)
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
