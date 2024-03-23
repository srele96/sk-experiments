// Do not try to understand the "why" of the code in this file. The answer is:
// BECAUSE I THOUGHT IT WOULD BE INTERESTING TO TRY IT OUT.
package org.example

import com.github.ajalt.clikt.core.CliktCommand
import com.github.ajalt.clikt.parameters.options.default
import com.github.ajalt.clikt.parameters.options.help
import com.github.ajalt.clikt.parameters.options.option
import com.github.ajalt.clikt.parameters.options.prompt
import com.github.ajalt.clikt.parameters.types.int
import com.mongodb.ConnectionString
import com.mongodb.MongoClientSettings
import com.mongodb.kotlin.client.*
import kotlinx.coroutines.*

class Hello : CliktCommand() {
    val count: Int by option().int().default(1).help("Number of greetings")
    val name: String by option().prompt("Your name").help("The person to greet")

    override fun run() {
        repeat(count) { echo("Hello $name") }
    }
}

data class Service(val foo: String, val bar: String, val baz: Int)

interface Callable {
    operator fun invoke()

    fun bar()
}

val callme =
    object : Callable {
        override fun invoke() {
            println("foo is called")
        }

        override fun bar() {
            println("bar is called")
        }
    }

data class User(val userId: String, val user: String, val db: String)

fun main(args: Array<String>) = runBlocking {
    // Run some coroutine... It has been a long time since i had to figure out how do javascript
    // promises work.
    // Actually i don't remember using promises that much lately. Actually it feels like at work we
    // were doing administrative work more than programming. Fuck!

    launch {
        delay(1000L)
        println("written at the end...")
    }
    println(Service(foo = "fooer", bar = "barer", baz = 5))
    fun Service.something(): Service {
        println(this)
        return this
    }
    println(Service(foo = "duh..", bar = "kek...", baz = 3).something())
    Hello().main(args)

    // An interesting play with callback functions in kotlin...
    fun oopsie(x: String, f: (String) -> String): (String) -> String {
        return { a -> f(a + " ret") + " " + x }
    }
    println(oopsie("something", { something -> something + " last" })("final"))

    // The passwords are embeded within a docker-compose.yml file.
    // val uri = "mongodb://rootuser:rootpass@localhost:27017/"
    // val uri = "mongodb://service:servicepass@localhost:27017/"
    val uri = "mongodb://serviceowner:serviceownerpass@localhost:27017/"
    val settings =
        MongoClientSettings.builder()
            .applyConnectionString(ConnectionString(uri))
            .retryWrites(true)
            .build()
    val mongoClient = MongoClient.create(settings)
    mongoClient.listDatabaseNames().forEach { dbName -> println("dbname = " + dbName) }
    val database = mongoClient.getDatabase("admin")
    database.listCollections().forEach { name -> println(name) }
    println("users")
    database.getCollection<User>("users").find().forEach { user: User -> println(user) }
    mongoClient.close()
}
