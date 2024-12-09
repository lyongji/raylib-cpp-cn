local copy = function (target)
        import("core.project.config")
        os.cp("$(scriptdir)/resources", "$(buildir)/$(host)/$(arch)/$(mode)")
        print("资源:%s","$(buildir)/$(host)/$(arch)/$(mode)")
    end

target("textures_bunnymark", {kind = "binary", files = "textures_bunnymark.cpp",after_build = copy})
target("textures_image_drawing", {kind = "binary", files = "textures_image_drawing.cpp",after_build = copy})
target("textures_image_loading", {kind = "binary", files = "textures_image_loading.cpp",after_build = copy})

