name := "constellations-server"
version := "1.0"
scalaVersion := "2.11.7"

libraryDependencies ++= Seq(
  "org.scala-lang" %% "scala-pickling" % "0.9.1",
  "com.typesafe.akka" %% "akka-actor" % "2.4.1",
  "com.typesafe.akka" %% "akka-testkit" % "2.4.1" % "test",
  "org.scalatest" %% "scalatest" % "2.2.6" % "test"
)

scalacOptions ++= Seq(
  "-deprecation",
  "-feature",
  "-unchecked",
  "-Xfatal-warnings",
  "-Xlint:_"
)

fork := true
cancelable in Global := true

assemblyJarName in assembly := "constellations-server.jar"
test in assembly := {}
mainClass in assembly := Some("constellations.server.Main")
