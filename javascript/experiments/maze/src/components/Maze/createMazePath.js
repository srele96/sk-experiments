/**
 * Create maze path for already sorted edges.
 */
function createMazePath(edges, provide) {
  class Component {
    constructor(vertex, size) {
      this.representativeVertex = vertex;
      this.size = size;
    }
  }

  class UnionFind {
    #components;

    constructor() {
      this.#components = this.#createComponents();
    }

    #createComponents() {
      const components = edges.reduce((previousValue, edge) => {
        const size = 1;
        const vertexOneComponent = new Component(edge.vertexOne, size);
        const vertexTwoComponent = new Component(edge.vertexTwo, size);

        previousValue.set(edge.vertexOne, vertexOneComponent);
        previousValue.set(edge.vertexTwo, vertexTwoComponent);

        return previousValue;
      }, new Map());

      return components;
    }

    #findRepresentativeComponent(vertex) {
      let currentVertex = vertex;
      let currentComponent = this.#components.get(currentVertex);

      while (currentVertex !== currentComponent.representativeVertex) {
        currentVertex = currentComponent.representativeVertex;
        currentComponent = this.#components.get(currentVertex);
      }

      return currentComponent;
    }

    areTheSameComponent(vertexOne, vertexTwo) {
      const vertexOneComponent = this.#findRepresentativeComponent(vertexOne);
      const vertexTwoComponent = this.#findRepresentativeComponent(vertexTwo);

      const areTheSame =
        vertexOneComponent.representativeVertex ==
        vertexTwoComponent.representativeVertex;

      return areTheSame;
    }

    #setRepresentative(componentOne, componentTwo) {
      this.#components.set(componentOne.representativeVertex, {
        ...componentOne,
        representativeVertex: componentTwo.representativeVertex,
      });
    }

    #updateSize(componentOne, componentTwo) {
      const newSize = componentOne.size + componentTwo.size;
      this.#components.set(componentOne.representativeVertex, {
        ...componentOne,
        size: newSize,
      });
    }

    unite(vertexOne, vertexTwo) {
      const vertexOneComponent = this.#findRepresentativeComponent(vertexOne);
      const vertexTwoComponent = this.#findRepresentativeComponent(vertexTwo);

      const vertexOneComponentIsLarger =
        vertexOneComponent.size > vertexTwoComponent.size;

      if (vertexOneComponentIsLarger) {
        this.#setRepresentative(vertexTwoComponent, vertexOneComponent);
        this.#updateSize(vertexOneComponent, vertexTwoComponent);
      } else {
        this.#setRepresentative(vertexOneComponent, vertexTwoComponent);
        this.#updateSize(vertexTwoComponent, vertexOneComponent);
      }
    }
  }

  let unionFind = new UnionFind();

  edges.forEach((edge) => {
    if (!unionFind.areTheSameComponent(edge.vertexOne, edge.vertexTwo)) {
      unionFind.unite(edge.vertexOne, edge.vertexTwo);

      provide(edge.cell);
    }
  });
}

export { createMazePath };
