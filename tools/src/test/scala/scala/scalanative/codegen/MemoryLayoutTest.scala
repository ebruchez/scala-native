package scala.scalanative
package codegen

import org.junit.Assert._
import org.junit.Test

class MemoryLayoutTest {

  private def platformInfo(
      triple: String,
      is32Bit: Boolean,
      targetsWindows: Boolean = false
  ): PlatformInfo =
    PlatformInfo(
      targetTriple = Some(triple),
      targetsWindows = targetsWindows,
      is32Bit = is32Bit,
      isMultithreadingEnabled = false,
      useOpaquePointers = true,
      useGCYieldPointTraps = false,
      useCxxExceptions = false
    )

  @Test
  def longAndDoubleAlignmentOn32BitArm(): Unit = {
    implicit val platform: PlatformInfo =
      platformInfo("thumbv6m-none-eabi", is32Bit = true)
    assertEquals(8L, MemoryLayout.alignmentOf(nir.Type.Long))
    assertEquals(8L, MemoryLayout.alignmentOf(nir.Type.Double))
    assertEquals(4L, MemoryLayout.alignmentOf(nir.Type.Ptr))

    val layout = MemoryLayout(Seq(nir.Type.Ptr, nir.Type.Long))
    assertEquals(
      Seq(
        MemoryLayout.PositionedType(nir.Type.Ptr, 0L),
        MemoryLayout.PositionedType(nir.Type.Long, 8L)
      ),
      layout.tys
    )
    assertEquals(16L, layout.size)
  }

  @Test
  def longAndDoubleAlignmentOn32BitRiscV(): Unit = {
    implicit val platform: PlatformInfo =
      platformInfo("riscv32-unknown-none-elf", is32Bit = true)
    assertEquals(8L, MemoryLayout.alignmentOf(nir.Type.Long))
    assertEquals(8L, MemoryLayout.alignmentOf(nir.Type.Double))
  }

  @Test
  def longAndDoubleAlignmentOn32BitX86Unix(): Unit = {
    implicit val platform: PlatformInfo =
      platformInfo("i686-unknown-linux-gnu", is32Bit = true)
    assertEquals(4L, MemoryLayout.alignmentOf(nir.Type.Long))
    assertEquals(4L, MemoryLayout.alignmentOf(nir.Type.Double))
  }

  @Test
  def longAndDoubleAlignmentOn32BitX86Windows(): Unit = {
    implicit val platform: PlatformInfo =
      platformInfo(
        "i686-pc-windows-msvc",
        is32Bit = true,
        targetsWindows = true
      )
    assertEquals(8L, MemoryLayout.alignmentOf(nir.Type.Long))
    assertEquals(8L, MemoryLayout.alignmentOf(nir.Type.Double))
  }
}
