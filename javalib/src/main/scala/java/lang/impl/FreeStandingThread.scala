package java.lang.impl

import scala.scalanative.annotation.alwaysinline
import scala.scalanative.runtime.NativeThread
import scala.scalanative.unsafe.CInt

private[java] class FreeStandingThread(
    val thread: Thread,
    userDefinedStackSize: scala.Long,
    override protected val isExternalThread: Boolean = false
) extends NativeThread {

  override def companion: NativeThread.Companion = FreeStandingThread

  override def stackSize: scala.Int = 0

  if (!isMainThread && !isExternalThread) {
    throw new LinkageError(
      "Multithreading support disabled on freestanding target - cannot create new threads"
    )
  }

  override def setPriority(priority: CInt): Unit = ()

  override def interrupt(): Unit = ()

  override protected def park(time: Long, isAbsolute: Boolean): Unit = ()

  override def unpark(): Unit = ()

  override def sleep(millis: Long): Unit = ()

  override def sleepNanos(nanos: Int): Unit = ()
}

private[lang] object FreeStandingThread extends NativeThread.Companion {
  override type Impl = FreeStandingThread

  @alwaysinline def create(
      thread: Thread,
      stackSize: Long
  ): FreeStandingThread =
    new FreeStandingThread(thread, stackSize)

  def adoptCurrentThread(thread: Thread): FreeStandingThread =
    new FreeStandingThread(thread, 0L, isExternalThread = true)

  @alwaysinline def yieldThread(): Unit = ()

  override def defaultOSStackSize: Long = 0L
}
