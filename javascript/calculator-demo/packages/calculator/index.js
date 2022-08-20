// nodejs looks up absolute imports in node_modules
// we can import these because each package gets installed in root node_modules
import { add } from 'add';
import { subtract } from 'subtract';
import { multiply } from 'multiply';
import { divide } from 'divide';

// provide named and default exports, re-exporting doesn't make sense
// but this demonstrates how to use monorepo packages to split the logic
// because here we can use add, subtract, multiply and divide to build
// another layer of abstraction
export { add, subtract, multiply, divide };
export default { add, subtract, multiply, divide };
