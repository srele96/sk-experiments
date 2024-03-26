// TODO: Explore the `plugins {}` block in this file. Consequence of: 7156f3e143455bc03ee4681ed4af2079daf5a35a

// TODO: Format the file better.
// Questions:
//     - Why does it work?
//     - Why did I have to add alias to the root build.gradle.kts and apply plugin within subprojects block?
//       I can make sense of it that root doesn't automatically apply plugins even if they are defined in the root which if parent of subprojects. Subprojects may not want the plugin at all.
//       It makes sense that we can't apply a plugin from this file if gradle doesn't have it at this point in time. Only subprojects have it if they declare it within plugins {} block.
plugins {
    // Apply the org.jetbrains.kotlin.jvm Plugin to add support for Kotlin.
    alias(libs.plugins.jvm)
}

// Interesting... So we can access more properties here?
// println("outside = ${name}") // Leave as a reminder to experiment.

// TODO: An idea to explore.
// I assume these are called by whoever gradle set up to be called... and we may access some properties. Within subprojects we may access name of the subproject... interesting...
// TODO: Replace with a better gradle plugin applying practices. Gradle documentaiton says not to use subprojects {} block to configure plugins.
// https://discuss.gradle.org/t/multi-module-project-how-where-to-apply-plugins/46701
subprojects {
    // TODO: An idea to explore.
    // Aha... so this block can be considered a lambda... but it may also define some properties in kotlin style? Am I right?
    // println("inside = ${name}") // Leave as a reminder to experiment.
    apply(plugin = "org.jetbrains.kotlin.jvm")

    repositories {
        mavenCentral()
    }
}
