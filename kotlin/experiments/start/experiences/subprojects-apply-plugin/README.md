# Resources

- https://github.com/software-mansion/react-native-gesture-handler/issues/2307 
- https://stackoverflow.com/questions/52562735/plugin-id-org-jetbrains-kotlin-jvm-version-1-2-71-was-not-found-in-any
- https://stackoverflow.com/questions/69261015/how-to-properly-add-gradle-plugin-to-multiproject
- https://docs.gradle.org/current/userguide/application_plugin.html
- https://docs.gradle.org/current/userguide/intro_multi_project_builds.html
- https://docs.gradle.org/current/userguide/building_java_projects.html#sec:java_source_sets

## Outputs

```terminal
FAILURE: Build failed with an exception.

* Where:
Build file '/home/srecko/Documents/projects/ct-sk-experiments/sk-experiments/kotlin/experiments/start/build.gradle.kts' line: 11

* What went wrong:
Plugin with id 'org.jetbrains.kotlin.jvm' not found.

* Try:
> Run with --stacktrace option to get the stack trace.
> Run with --info or --debug option to get more log output.
> Run with --scan to get full insights.
> Get more help at https://help.gradle.org.

BUILD FAILED in 988ms
```

```terminal
> Configure project :
e: file:///home/srecko/Documents/projects/ct-sk-experiments/sk-experiments/kotlin/experiments/start/build.gradle.kts:18:5: Unresolved reference: classpath

FAILURE: Build failed with an exception.

* Where:
Build file '/home/srecko/Documents/projects/ct-sk-experiments/sk-experiments/kotlin/experiments/start/build.gradle.kts' line: 18

* What went wrong:
Script compilation error:

  Line 18:     classpath("org.jetbrains.kotlin:kotlin-gradle-plugin:2.0.0")
               ^ Unresolved reference: classpath

1 error

* Try:
> Run with --stacktrace option to get the stack trace.
> Run with --info or --debug option to get more log output.
> Run with --scan to get full insights.
> Get more help at https://help.gradle.org.

BUILD FAILED in 715ms
```

```terminal
> Configure project :
e: file:///home/srecko/Documents/projects/ct-sk-experiments/sk-experiments/kotlin/experiments/start/build.gradle.kts:10:5: Using 'plugins(PluginDependenciesSpec.() -> Unit): Nothing' is an error. The plugins {} block must not be used here. If you need to apply a plugin imperatively, please use apply<PluginType>() or apply(plugin = "id") instead.
w: file:///home/srecko/Documents/projects/ct-sk-experiments/sk-experiments/kotlin/experiments/start/build.gradle.kts:14:5: Unreachable code
w: file:///home/srecko/Documents/projects/ct-sk-experiments/sk-experiments/kotlin/experiments/start/build.gradle.kts:16:5: Unreachable code

FAILURE: Build failed with an exception.

* Where:
Build file '/home/srecko/Documents/projects/ct-sk-experiments/sk-experiments/kotlin/experiments/start/build.gradle.kts' line: 10

* What went wrong:
Script compilation error:

  Line 10:     plugins {
               ^ Using 'plugins(PluginDependenciesSpec.() -> Unit): Nothing' is an error. The plugins {} block must not be used here. If you need to apply a plugin imperatively, please use apply<PluginType>() or apply(plugin = "id") instead.

1 error

* Try:
> Run with --stacktrace option to get the stack trace.
> Run with --info or --debug option to get more log output.
> Run with --scan to get full insights.
> Get more help at https://help.gradle.org.

BUILD FAILED in 921ms
```

