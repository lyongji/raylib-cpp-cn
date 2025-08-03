local copy = function (target)
        import("core.project.config")
        os.cp("$(scriptdir)/resources", "$(builddir)/$(host)/$(arch)/$(mode)")
        print("资源:%s","$(builddir)/$(host)/$(arch)/$(mode)")
    end

target("audio_music_stream", {kind = "binary", files = "audio_music_stream.cpp",after_build = copy})
 
target("audio_sound_loading", {kind = "binary", files = "audio_sound_loading.cpp",after_build = copy})
 