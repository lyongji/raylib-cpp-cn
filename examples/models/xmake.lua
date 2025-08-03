local copy = function (target)
        import("core.project.config")
        os.cp("$(scriptdir)/resources", "$(builddir)/$(host)/$(arch)/$(mode)")
        print("资源:%s","$(builddir)/$(host)/$(arch)/$(mode)")
    end

target("models_billboard", {kind = "binary", files = "models_billboard.cpp",after_build = copy})
target("models_first_person_maze", {kind = "binary", files = "models_first_person_maze.cpp",after_build = copy})
 