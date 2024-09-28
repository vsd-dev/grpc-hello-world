// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: inference.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_inference_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_inference_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3019000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3019005 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_bases.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_inference_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_inference_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxiliaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[3]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const uint32_t offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_inference_2eproto;
namespace inference {
class Empty;
struct EmptyDefaultTypeInternal;
extern EmptyDefaultTypeInternal _Empty_default_instance_;
class Request;
struct RequestDefaultTypeInternal;
extern RequestDefaultTypeInternal _Request_default_instance_;
class Response;
struct ResponseDefaultTypeInternal;
extern ResponseDefaultTypeInternal _Response_default_instance_;
}  // namespace inference
PROTOBUF_NAMESPACE_OPEN
template<> ::inference::Empty* Arena::CreateMaybeMessage<::inference::Empty>(Arena*);
template<> ::inference::Request* Arena::CreateMaybeMessage<::inference::Request>(Arena*);
template<> ::inference::Response* Arena::CreateMaybeMessage<::inference::Response>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace inference {

// ===================================================================

class Request final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:inference.Request) */ {
 public:
  inline Request() : Request(nullptr) {}
  ~Request() override;
  explicit constexpr Request(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  Request(const Request& from);
  Request(Request&& from) noexcept
    : Request() {
    *this = ::std::move(from);
  }

  inline Request& operator=(const Request& from) {
    CopyFrom(from);
    return *this;
  }
  inline Request& operator=(Request&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const Request& default_instance() {
    return *internal_default_instance();
  }
  static inline const Request* internal_default_instance() {
    return reinterpret_cast<const Request*>(
               &_Request_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(Request& a, Request& b) {
    a.Swap(&b);
  }
  inline void Swap(Request* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(Request* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  Request* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<Request>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const Request& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom(const Request& from);
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to, const ::PROTOBUF_NAMESPACE_ID::Message& from);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  uint8_t* _InternalSerialize(
      uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(Request* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "inference.Request";
  }
  protected:
  explicit Request(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kImageDataFieldNumber = 6,
    kBatchIndexFieldNumber = 1,
    kBatchSizeFieldNumber = 2,
    kImageHeightFieldNumber = 3,
    kImageWidthFieldNumber = 4,
    kImageChannelsFieldNumber = 5,
  };
  // bytes image_data = 6;
  void clear_image_data();
  const std::string& image_data() const;
  template <typename ArgT0 = const std::string&, typename... ArgT>
  void set_image_data(ArgT0&& arg0, ArgT... args);
  std::string* mutable_image_data();
  PROTOBUF_NODISCARD std::string* release_image_data();
  void set_allocated_image_data(std::string* image_data);
  private:
  const std::string& _internal_image_data() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_image_data(const std::string& value);
  std::string* _internal_mutable_image_data();
  public:

  // int32 batch_index = 1;
  void clear_batch_index();
  int32_t batch_index() const;
  void set_batch_index(int32_t value);
  private:
  int32_t _internal_batch_index() const;
  void _internal_set_batch_index(int32_t value);
  public:

  // int32 batch_size = 2;
  void clear_batch_size();
  int32_t batch_size() const;
  void set_batch_size(int32_t value);
  private:
  int32_t _internal_batch_size() const;
  void _internal_set_batch_size(int32_t value);
  public:

  // int32 image_height = 3;
  void clear_image_height();
  int32_t image_height() const;
  void set_image_height(int32_t value);
  private:
  int32_t _internal_image_height() const;
  void _internal_set_image_height(int32_t value);
  public:

  // int32 image_width = 4;
  void clear_image_width();
  int32_t image_width() const;
  void set_image_width(int32_t value);
  private:
  int32_t _internal_image_width() const;
  void _internal_set_image_width(int32_t value);
  public:

  // int32 image_channels = 5;
  void clear_image_channels();
  int32_t image_channels() const;
  void set_image_channels(int32_t value);
  private:
  int32_t _internal_image_channels() const;
  void _internal_set_image_channels(int32_t value);
  public:

  // @@protoc_insertion_point(class_scope:inference.Request)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr image_data_;
  int32_t batch_index_;
  int32_t batch_size_;
  int32_t image_height_;
  int32_t image_width_;
  int32_t image_channels_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_inference_2eproto;
};
// -------------------------------------------------------------------

class Response final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:inference.Response) */ {
 public:
  inline Response() : Response(nullptr) {}
  ~Response() override;
  explicit constexpr Response(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  Response(const Response& from);
  Response(Response&& from) noexcept
    : Response() {
    *this = ::std::move(from);
  }

  inline Response& operator=(const Response& from) {
    CopyFrom(from);
    return *this;
  }
  inline Response& operator=(Response&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const Response& default_instance() {
    return *internal_default_instance();
  }
  static inline const Response* internal_default_instance() {
    return reinterpret_cast<const Response*>(
               &_Response_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  friend void swap(Response& a, Response& b) {
    a.Swap(&b);
  }
  inline void Swap(Response* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(Response* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  Response* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<Response>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const Response& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom(const Response& from);
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to, const ::PROTOBUF_NAMESPACE_ID::Message& from);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  uint8_t* _InternalSerialize(
      uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(Response* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "inference.Response";
  }
  protected:
  explicit Response(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kClassificationFieldNumber = 2,
    kBatchIndexFieldNumber = 1,
  };
  // repeated int32 classification = 2;
  int classification_size() const;
  private:
  int _internal_classification_size() const;
  public:
  void clear_classification();
  private:
  int32_t _internal_classification(int index) const;
  const ::PROTOBUF_NAMESPACE_ID::RepeatedField< int32_t >&
      _internal_classification() const;
  void _internal_add_classification(int32_t value);
  ::PROTOBUF_NAMESPACE_ID::RepeatedField< int32_t >*
      _internal_mutable_classification();
  public:
  int32_t classification(int index) const;
  void set_classification(int index, int32_t value);
  void add_classification(int32_t value);
  const ::PROTOBUF_NAMESPACE_ID::RepeatedField< int32_t >&
      classification() const;
  ::PROTOBUF_NAMESPACE_ID::RepeatedField< int32_t >*
      mutable_classification();

  // int32 batch_index = 1;
  void clear_batch_index();
  int32_t batch_index() const;
  void set_batch_index(int32_t value);
  private:
  int32_t _internal_batch_index() const;
  void _internal_set_batch_index(int32_t value);
  public:

  // @@protoc_insertion_point(class_scope:inference.Response)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::RepeatedField< int32_t > classification_;
  mutable std::atomic<int> _classification_cached_byte_size_;
  int32_t batch_index_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_inference_2eproto;
};
// -------------------------------------------------------------------

class Empty final :
    public ::PROTOBUF_NAMESPACE_ID::internal::ZeroFieldsBase /* @@protoc_insertion_point(class_definition:inference.Empty) */ {
 public:
  inline Empty() : Empty(nullptr) {}
  explicit constexpr Empty(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  Empty(const Empty& from);
  Empty(Empty&& from) noexcept
    : Empty() {
    *this = ::std::move(from);
  }

  inline Empty& operator=(const Empty& from) {
    CopyFrom(from);
    return *this;
  }
  inline Empty& operator=(Empty&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const Empty& default_instance() {
    return *internal_default_instance();
  }
  static inline const Empty* internal_default_instance() {
    return reinterpret_cast<const Empty*>(
               &_Empty_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    2;

  friend void swap(Empty& a, Empty& b) {
    a.Swap(&b);
  }
  inline void Swap(Empty* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(Empty* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  Empty* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<Empty>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::internal::ZeroFieldsBase::CopyFrom;
  inline void CopyFrom(const Empty& from) {
    ::PROTOBUF_NAMESPACE_ID::internal::ZeroFieldsBase::CopyImpl(this, from);
  }
  using ::PROTOBUF_NAMESPACE_ID::internal::ZeroFieldsBase::MergeFrom;
  void MergeFrom(const Empty& from) {
    ::PROTOBUF_NAMESPACE_ID::internal::ZeroFieldsBase::MergeImpl(this, from);
  }
  public:

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "inference.Empty";
  }
  protected:
  explicit Empty(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  private:
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // @@protoc_insertion_point(class_scope:inference.Empty)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_inference_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// Request

// int32 batch_index = 1;
inline void Request::clear_batch_index() {
  batch_index_ = 0;
}
inline int32_t Request::_internal_batch_index() const {
  return batch_index_;
}
inline int32_t Request::batch_index() const {
  // @@protoc_insertion_point(field_get:inference.Request.batch_index)
  return _internal_batch_index();
}
inline void Request::_internal_set_batch_index(int32_t value) {
  
  batch_index_ = value;
}
inline void Request::set_batch_index(int32_t value) {
  _internal_set_batch_index(value);
  // @@protoc_insertion_point(field_set:inference.Request.batch_index)
}

// int32 batch_size = 2;
inline void Request::clear_batch_size() {
  batch_size_ = 0;
}
inline int32_t Request::_internal_batch_size() const {
  return batch_size_;
}
inline int32_t Request::batch_size() const {
  // @@protoc_insertion_point(field_get:inference.Request.batch_size)
  return _internal_batch_size();
}
inline void Request::_internal_set_batch_size(int32_t value) {
  
  batch_size_ = value;
}
inline void Request::set_batch_size(int32_t value) {
  _internal_set_batch_size(value);
  // @@protoc_insertion_point(field_set:inference.Request.batch_size)
}

// int32 image_height = 3;
inline void Request::clear_image_height() {
  image_height_ = 0;
}
inline int32_t Request::_internal_image_height() const {
  return image_height_;
}
inline int32_t Request::image_height() const {
  // @@protoc_insertion_point(field_get:inference.Request.image_height)
  return _internal_image_height();
}
inline void Request::_internal_set_image_height(int32_t value) {
  
  image_height_ = value;
}
inline void Request::set_image_height(int32_t value) {
  _internal_set_image_height(value);
  // @@protoc_insertion_point(field_set:inference.Request.image_height)
}

// int32 image_width = 4;
inline void Request::clear_image_width() {
  image_width_ = 0;
}
inline int32_t Request::_internal_image_width() const {
  return image_width_;
}
inline int32_t Request::image_width() const {
  // @@protoc_insertion_point(field_get:inference.Request.image_width)
  return _internal_image_width();
}
inline void Request::_internal_set_image_width(int32_t value) {
  
  image_width_ = value;
}
inline void Request::set_image_width(int32_t value) {
  _internal_set_image_width(value);
  // @@protoc_insertion_point(field_set:inference.Request.image_width)
}

// int32 image_channels = 5;
inline void Request::clear_image_channels() {
  image_channels_ = 0;
}
inline int32_t Request::_internal_image_channels() const {
  return image_channels_;
}
inline int32_t Request::image_channels() const {
  // @@protoc_insertion_point(field_get:inference.Request.image_channels)
  return _internal_image_channels();
}
inline void Request::_internal_set_image_channels(int32_t value) {
  
  image_channels_ = value;
}
inline void Request::set_image_channels(int32_t value) {
  _internal_set_image_channels(value);
  // @@protoc_insertion_point(field_set:inference.Request.image_channels)
}

// bytes image_data = 6;
inline void Request::clear_image_data() {
  image_data_.ClearToEmpty();
}
inline const std::string& Request::image_data() const {
  // @@protoc_insertion_point(field_get:inference.Request.image_data)
  return _internal_image_data();
}
template <typename ArgT0, typename... ArgT>
inline PROTOBUF_ALWAYS_INLINE
void Request::set_image_data(ArgT0&& arg0, ArgT... args) {
 
 image_data_.SetBytes(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, static_cast<ArgT0 &&>(arg0), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:inference.Request.image_data)
}
inline std::string* Request::mutable_image_data() {
  std::string* _s = _internal_mutable_image_data();
  // @@protoc_insertion_point(field_mutable:inference.Request.image_data)
  return _s;
}
inline const std::string& Request::_internal_image_data() const {
  return image_data_.Get();
}
inline void Request::_internal_set_image_data(const std::string& value) {
  
  image_data_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, value, GetArenaForAllocation());
}
inline std::string* Request::_internal_mutable_image_data() {
  
  return image_data_.Mutable(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, GetArenaForAllocation());
}
inline std::string* Request::release_image_data() {
  // @@protoc_insertion_point(field_release:inference.Request.image_data)
  return image_data_.Release(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArenaForAllocation());
}
inline void Request::set_allocated_image_data(std::string* image_data) {
  if (image_data != nullptr) {
    
  } else {
    
  }
  image_data_.SetAllocated(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), image_data,
      GetArenaForAllocation());
#ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (image_data_.IsDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited())) {
    image_data_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), "", GetArenaForAllocation());
  }
#endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:inference.Request.image_data)
}

// -------------------------------------------------------------------

// Response

// int32 batch_index = 1;
inline void Response::clear_batch_index() {
  batch_index_ = 0;
}
inline int32_t Response::_internal_batch_index() const {
  return batch_index_;
}
inline int32_t Response::batch_index() const {
  // @@protoc_insertion_point(field_get:inference.Response.batch_index)
  return _internal_batch_index();
}
inline void Response::_internal_set_batch_index(int32_t value) {
  
  batch_index_ = value;
}
inline void Response::set_batch_index(int32_t value) {
  _internal_set_batch_index(value);
  // @@protoc_insertion_point(field_set:inference.Response.batch_index)
}

// repeated int32 classification = 2;
inline int Response::_internal_classification_size() const {
  return classification_.size();
}
inline int Response::classification_size() const {
  return _internal_classification_size();
}
inline void Response::clear_classification() {
  classification_.Clear();
}
inline int32_t Response::_internal_classification(int index) const {
  return classification_.Get(index);
}
inline int32_t Response::classification(int index) const {
  // @@protoc_insertion_point(field_get:inference.Response.classification)
  return _internal_classification(index);
}
inline void Response::set_classification(int index, int32_t value) {
  classification_.Set(index, value);
  // @@protoc_insertion_point(field_set:inference.Response.classification)
}
inline void Response::_internal_add_classification(int32_t value) {
  classification_.Add(value);
}
inline void Response::add_classification(int32_t value) {
  _internal_add_classification(value);
  // @@protoc_insertion_point(field_add:inference.Response.classification)
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedField< int32_t >&
Response::_internal_classification() const {
  return classification_;
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedField< int32_t >&
Response::classification() const {
  // @@protoc_insertion_point(field_list:inference.Response.classification)
  return _internal_classification();
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedField< int32_t >*
Response::_internal_mutable_classification() {
  return &classification_;
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedField< int32_t >*
Response::mutable_classification() {
  // @@protoc_insertion_point(field_mutable_list:inference.Response.classification)
  return _internal_mutable_classification();
}

// -------------------------------------------------------------------

// Empty

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------

// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace inference

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_inference_2eproto
