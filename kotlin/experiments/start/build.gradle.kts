//plugins {
//     alias(libs.plugins.jvm) // where does this come from if it's available?
//}
//
//repositories {
//    mavenCentral()
//}

// Why does it work?
// Why did I have to add alias to the root build.gradle.kts and apply plugin within subprojects block?
// I can make sense of it that root doesn't automatically apply plugins even if they are defined in the root which if parent of subprojects. Subprojects may not want the plugin at all.
// It makes sense that we can't apply a plugin from this file if gradle doesn't have it at this point in time. Only subprojects have it if they declare it within plugins {} block.
plugins {
    // Apply the org.jetbrains.kotlin.jvm Plugin to add support for Kotlin.
    alias(libs.plugins.jvm)
}

// Interesting... So we can access more properties here?
println("outside = ${name}")
// I assume these are called by whoever gradle set up to be called... and we may access some properties. Within subprojects we may access name of the subproject... interesting...
subprojects {
    // Aha... so this block can be considered a lambda... but it may also define some properties in kotlin style? Am I right?
    println("inside = ${name}")
    apply(plugin = "org.jetbrains.kotlin.jvm")

    repositories {
        mavenCentral()
    }
}
