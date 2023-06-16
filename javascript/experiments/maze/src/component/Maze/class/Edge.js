class Edge {
  constructor(vertexOne, vertexTwo, cell) {
    this.vertexOne = vertexOne;
    this.vertexTwo = vertexTwo;
    this.cell = cell;
    this.weight = this.#createRandomPathWeight();
  }

  #createRandomPathWeight() {
    const weight = new Uint32Array(1);
    // Try to get as close to true randomness as possible.
    crypto.getRandomValues(weight);
    return weight[0];
  }
}

export { Edge };
