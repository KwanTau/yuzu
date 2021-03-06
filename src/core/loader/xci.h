// Copyright 2018 yuzu emulator team
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#pragma once

#include <memory>
#include "common/common_types.h"
#include "core/file_sys/vfs.h"
#include "core/loader/loader.h"

namespace FileSys {
class NACP;
class XCI;
} // namespace FileSys

namespace Loader {

class AppLoader_NCA;

/// Loads an XCI file
class AppLoader_XCI final : public AppLoader {
public:
    explicit AppLoader_XCI(FileSys::VirtualFile file);
    ~AppLoader_XCI() override;

    /**
     * Returns the type of the file
     * @param file std::shared_ptr<VfsFile> open file
     * @return FileType found, or FileType::Error if this loader doesn't know it
     */
    static FileType IdentifyType(const FileSys::VirtualFile& file);

    FileType GetFileType() const override {
        return IdentifyType(file);
    }

    LoadResult Load(Kernel::Process& process) override;

    ResultStatus ReadRomFS(FileSys::VirtualFile& file) override;
    u64 ReadRomFSIVFCOffset() const override;
    ResultStatus ReadUpdateRaw(FileSys::VirtualFile& file) override;
    ResultStatus ReadProgramId(u64& out_program_id) override;
    ResultStatus ReadIcon(std::vector<u8>& buffer) override;
    ResultStatus ReadTitle(std::string& title) override;
    ResultStatus ReadControlData(FileSys::NACP& control) override;
    ResultStatus ReadManualRomFS(FileSys::VirtualFile& file) override;

    ResultStatus ReadBanner(std::vector<u8>& buffer) override;
    ResultStatus ReadLogo(std::vector<u8>& buffer) override;

private:
    std::unique_ptr<FileSys::XCI> xci;
    std::unique_ptr<AppLoader_NCA> nca_loader;

    FileSys::VirtualFile icon_file;
    std::unique_ptr<FileSys::NACP> nacp_file;
};

} // namespace Loader
