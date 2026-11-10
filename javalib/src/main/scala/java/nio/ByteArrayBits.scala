package java.nio

import scala.scalanative.meta.LinktimeInfo.{is32BitPlatform, isFreeStanding}
import scala.scalanative.runtime.Intrinsics.{castIntToRawSize, elemRawPtr}
import scala.scalanative.runtime.{Intrinsics, RawPtr, toRawPtr}
import scala.scalanative.unsafe._

private[nio] object ByteArrayBits {
  def apply(
      array: Ptr[Byte],
      arrayOffset: Int,
      isBigEndian: Boolean,
      indexMultiplier: Int = 1
  ): ByteArrayBits =
    new ByteArrayBits(array, arrayOffset, isBigEndian, indexMultiplier)
}

@inline
private[nio] final class ByteArrayBits(
    array: Ptr[Byte],
    arrayOffset: Int,
    isBigEndian: Boolean,
    indexMultiplier: Int
) {

  @inline private def loadUByteAt(offset: Int): Int =
    Intrinsics.loadByte(
      elemRawPtr(toRawPtr(array), castIntToRawSize(offset))
    ) & 0xff

  @inline private def storeByteAt(offset: Int, b: Int): Unit =
    Intrinsics.storeByte(
      elemRawPtr(toRawPtr(array), castIntToRawSize(offset)),
      b.toByte
    )

  @inline private def isUnaligned2(idx: Int): Boolean =
    if (is32BitPlatform || isFreeStanding) (idx & 1) != 0 else false

  @inline private def isUnaligned4(idx: Int): Boolean =
    if (is32BitPlatform || isFreeStanding) (idx & 3) != 0 else false

  @inline private def isUnaligned8(ptr: RawPtr): Boolean =
    if (is32BitPlatform || isFreeStanding)
      (Intrinsics.castRawPtrToLong(ptr) & 7L) != 0L
    else false

  // API

  def loadChar(index: Int): Char = {
    val idx = indexMultiplier * index + arrayOffset
    val loaded =
      if (isUnaligned2(idx)) {
        (loadUByteAt(idx) | (loadUByteAt(idx + 1) << 8)).toChar
      } else {
        Intrinsics.loadChar(elemRawPtr(toRawPtr(array), castIntToRawSize(idx)))
      }
    if (isBigEndian) java.lang.Character.reverseBytes(loaded)
    else loaded
  }
  def loadShort(index: Int): Short = {
    val idx = indexMultiplier * index + arrayOffset
    val loaded =
      if (isUnaligned2(idx)) {
        (loadUByteAt(idx) | (loadUByteAt(idx + 1) << 8)).toShort
      } else {
        Intrinsics.loadShort(elemRawPtr(toRawPtr(array), castIntToRawSize(idx)))
      }
    if (isBigEndian) java.lang.Short.reverseBytes(loaded)
    else loaded
  }
  def loadInt(index: Int): Int = {
    val idx = indexMultiplier * index + arrayOffset
    val loaded =
      if (isUnaligned4(idx)) {
        loadUByteAt(idx) |
          (loadUByteAt(idx + 1) << 8) |
          (loadUByteAt(idx + 2) << 16) |
          (loadUByteAt(idx + 3) << 24)
      } else {
        Intrinsics.loadInt(elemRawPtr(toRawPtr(array), castIntToRawSize(idx)))
      }
    if (isBigEndian) java.lang.Integer.reverseBytes(loaded)
    else loaded
  }
  def loadLong(index: Int): Long = {
    val idx = indexMultiplier * index + arrayOffset
    val ptr = elemRawPtr(toRawPtr(array), castIntToRawSize(idx))
    val loaded =
      if (isUnaligned8(ptr)) {
        val lo = (loadUByteAt(idx) |
          (loadUByteAt(idx + 1) << 8) |
          (loadUByteAt(idx + 2) << 16) |
          (loadUByteAt(idx + 3) << 24)).toLong & 0xffffffffL
        val hi = (loadUByteAt(idx + 4) |
          (loadUByteAt(idx + 5) << 8) |
          (loadUByteAt(idx + 6) << 16) |
          (loadUByteAt(idx + 7) << 24)).toLong
        lo | (hi << 32)
      } else {
        Intrinsics.loadLong(ptr)
      }
    if (isBigEndian) java.lang.Long.reverseBytes(loaded)
    else loaded
  }
  def loadFloat(index: Int): Float =
    java.lang.Float.intBitsToFloat(loadInt(index))

  def loadDouble(index: Int): Double =
    java.lang.Double.longBitsToDouble(loadLong(index))

  def storeChar(index: Int, v: Char): Unit = {
    val idx = indexMultiplier * index + arrayOffset
    val ordered =
      if (isBigEndian) java.lang.Character.reverseBytes(v)
      else v
    if (isUnaligned2(idx)) {
      storeByteAt(idx, ordered.toInt)
      storeByteAt(idx + 1, ordered.toInt >>> 8)
    } else {
      Intrinsics.storeChar(
        elemRawPtr(toRawPtr(array), castIntToRawSize(idx)),
        ordered
      )
    }
  }

  def storeShort(index: Int, v: Short): Unit = {
    val idx = indexMultiplier * index + arrayOffset
    val ordered =
      if (isBigEndian) java.lang.Short.reverseBytes(v)
      else v
    if (isUnaligned2(idx)) {
      storeByteAt(idx, ordered.toInt)
      storeByteAt(idx + 1, ordered.toInt >>> 8)
    } else {
      Intrinsics.storeShort(
        elemRawPtr(toRawPtr(array), castIntToRawSize(idx)),
        ordered
      )
    }
  }
  def storeInt(index: Int, v: Int): Unit = {
    val idx = indexMultiplier * index + arrayOffset
    val ordered =
      if (isBigEndian) java.lang.Integer.reverseBytes(v)
      else v
    if (isUnaligned4(idx)) {
      storeByteAt(idx, ordered)
      storeByteAt(idx + 1, ordered >>> 8)
      storeByteAt(idx + 2, ordered >>> 16)
      storeByteAt(idx + 3, ordered >>> 24)
    } else {
      Intrinsics.storeInt(
        elemRawPtr(toRawPtr(array), castIntToRawSize(idx)),
        ordered
      )
    }
  }
  def storeLong(index: Int, v: Long): Unit = {
    val idx = indexMultiplier * index + arrayOffset
    val ordered =
      if (isBigEndian) java.lang.Long.reverseBytes(v)
      else v
    val ptr = elemRawPtr(toRawPtr(array), castIntToRawSize(idx))
    if (isUnaligned8(ptr)) {
      val lo = ordered.toInt
      val hi = (ordered >>> 32).toInt
      storeByteAt(idx, lo)
      storeByteAt(idx + 1, lo >>> 8)
      storeByteAt(idx + 2, lo >>> 16)
      storeByteAt(idx + 3, lo >>> 24)
      storeByteAt(idx + 4, hi)
      storeByteAt(idx + 5, hi >>> 8)
      storeByteAt(idx + 6, hi >>> 16)
      storeByteAt(idx + 7, hi >>> 24)
    } else {
      Intrinsics.storeLong(ptr, ordered)
    }
  }
  def storeFloat(index: Int, v: Float): Unit =
    storeInt(index, java.lang.Float.floatToIntBits(v))

  def storeDouble(index: Int, v: Double): Unit =
    storeLong(index, java.lang.Double.doubleToLongBits(v))
}
