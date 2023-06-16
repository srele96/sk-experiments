// A workaround because it doesn't provide type declarations or proper entry
// point to resolve the import. Since I created the library I know it's
// compatible with NodeJS, for now.
declare module '@flexos/elements/dist/flexos-elements.umd' {
  export interface Options {
    length: number;
  }

  export interface FlexosElement {
    order: number;
  }

  export interface SetMainElement {
    (main_element: number): FlexosElement[];
  }

  export function get_elements(options: Options): SetMainElement;
}
