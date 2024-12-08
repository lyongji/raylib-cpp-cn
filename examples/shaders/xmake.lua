local copy = function (target)
        import("core.project.config")
        os.cp("$(scriptdir)/resources", "$(buildir)/$(host)/$(arch)/$(mode)")
        print("资源:%s","$(buildir)/$(host)/$(arch)/$(mode)")
    end

target("shaders_basic_lighting", {kind = "binary", files = "shaders_basic_lighting.cpp",after_build = copy})
target("shaders_basic_pbr", {kind = "binary", files = "shaders_basic_pbr.cpp",after_build = copy})
target("shaders_texture_waves", {kind = "binary", files = "shaders_texture_waves.cpp",after_build = copy})