package constellations.server

object Main extends App {

  println("hello constellation")

  case class ConnectionRequest(nick: String)
  case class ConnectionRequestRes(uid: Int)

  case class MatchRequest(gameStyle: String, localPlayerCount: Int, totalPlayerCount: Int, desiredPlayers: String)
  case class MatchResquestRes(finalgameStyle: String)

  case class NewPlayerBrd(playerSlot: Int, playerUID: Int, playerNick: String, hatID: Int)

  case class PlayerLeaveBrd(playerSlot : Int)

  case class HatChange(hatID: Int)
  case class HatChangeBrd(uid: Int, hatID: Int)

  case class LeavePool(wantToLeave: Boolean)
  case class LeavePoolBrd(uid: Int, leave: Boolean)

  case class RunTaunt(tauntID : String)

  case class ReadyToGo(setReady: Boolean)
  case class ReadyToGoBrd(uid: Int, ready: Boolean)

  case class CountDown(secToStart: Int)

  case class MatchCanceled(error: String)

  case class MatchStartHandshake(ready: Boolean)

  case class MatchData(mapID: Int)

}
