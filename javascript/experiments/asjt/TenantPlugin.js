const path = require('path');
const fs = require('fs');

class Tenant {
  name = 'Tenant';
  overrideDirname = 'tenant';

  constructor({ tenant }) {
    this.tenant = tenant;
  }

  apply(compiler) {
    let resolveByDependency;
    // Collect extensions
    compiler.hooks.afterEnvironment.tap(this.name, () => {
      resolveByDependency = compiler.options.resolve.byDependency;
    });

    // Import tenant file if a directory is a subject for overriding.
    compiler.hooks.normalModuleFactory.tap(this.name, (nmf) => {
      // At this point I can check against the current tenant and I can accept
      // the custom configuration from a file where user can hint and map files
      // overriden. A more advanced features would be capable of tokens, syntax,
      // etc... Partial file overriding, and many features more.
      nmf.hooks.beforeResolve.tap(this.name, (resolveData) => {
        const { context, request, dependencyType } = resolveData;

        const requiredFileName = path.basename(request);
        const requiredFilePath = path.join(context, path.dirname(request));
        const requiredTenantDirPath = path.join(
          requiredFilePath,
          this.overrideDirname,
          this.tenant
        );
        const requiredTenantFilePath = path.join(
          requiredTenantDirPath,
          requiredFileName
        );

        for (const extension of resolveByDependency[dependencyType]
          .extensions) {
          const fullRequiredTenantFilePath = requiredTenantFilePath + extension;
          if (fs.existsSync(fullRequiredTenantFilePath)) {
            // Preserve the original import.
            const { dir, base, ext } = path.parse(request);
            // Manually append the dir path at the start so path.join doesn't
            // obliterate the relative imports.
            const tenantFilePath =
              dir +
              path.sep +
              path.join(this.overrideDirname, this.tenant, base, ext);

            resolveData.request = tenantFilePath;
          }
        }
      });
    });
  }
}

module.exports = Tenant;
