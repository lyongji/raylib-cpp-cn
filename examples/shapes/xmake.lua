local copy = function (target)
        import("core.project.config")
        os.cp("$(scriptdir)/resources", "$(buildir)/$(host)/$(arch)/$(mode)")
        print("资源:%s","$(buildir)/$(host)/$(arch)/$(mode)")
    end

target("shapes_collision_area", {kind = "binary", files = "shapes_collision_area.cpp",after_build = copy})
target("shapes_logo_raylib", {kind = "binary", files = "shapes_logo_raylib.cpp",after_build = copy})
