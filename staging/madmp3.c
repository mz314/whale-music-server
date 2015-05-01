#include <stdio.h>
#include <stdlib.h>

#include <mad.h>
#include <alsa/asoundlib.h>

typedef struct 
{
 unsigned char *start;
 size_t length;
} buffer;


int load_file(char *fn,buffer *buff);
void alsainit();
void play_chunk();
void checkerr();

enum mad_flow input(void *data,struct mad_stream *stream);
enum mad_flow output(void *data,struct mad_header const *header,struct mad_pcm *pcm);
enum mad_flow error(void *data,struct mad_stream *stream,struct mad_frame *frame);

int main()
{
  buffer buff;
  printf("libmad test\n");
  if (load_file("test.mp3",&buff)==1)
    printf("File seems ok.\n"); else {printf("File ERROR!\n"); exit(0); }
  alsainit();
  //disposing:
  free(buff.start);
  return 0;
}

void checkerr(int err)
{
 if (err<0)
 {printf("%s",snd_strerror(err));
  exit(0);}
}

void alsainit()
{
 snd_pcm_hw_params_t *hw_params;
 snd_pcm_sw_params_t *sw_params;
 snd_pcm_t *playback;
 int err,dir;
 err=snd_pcm_open(&playback,"plug:dmix",SND_PCM_STREAM_PLAYBACK,0);
 checkerr(err);
 err=snd_pcm_hw_params_malloc(&hw_params);
 checkerr(err);
 err=snd_pcm_hw_params_any(playback,hw_params);
 checkerr(err);
 err = snd_pcm_hw_params_set_access (playback, hw_params, SND_PCM_ACCESS_RW_INTERLEAVED);
 checkerr(err);
 err=snd_pcm_hw_params_set_rate_resample(playback, hw_params,1);
 checkerr(err);
 err=snd_pcm_hw_params_set_format (playback, hw_params, SND_PCM_FORMAT_S16_LE); //WARNING:
 checkerr(err);
 err = snd_pcm_hw_params_set_rate (playback, hw_params, 44100, 0);
 checkerr(err);
 err = snd_pcm_hw_params_set_channels (playback, hw_params, 2);
 checkerr(err);
 //frames=32;
 //err=snd_pcm_hw_params_set_period_size_near(playback,hw_params, &frames, &dir);
 //checkerr(err);
 err = snd_pcm_hw_params (playback, hw_params);
 checkerr(err);
 snd_pcm_hw_params_free (hw_params);
 err = snd_pcm_sw_params_malloc (&sw_params);
 checkerr(err);
 err = snd_pcm_sw_params_current (playback, sw_params);
 checkerr(err);
 err = snd_pcm_sw_params_set_avail_min (playback, sw_params, 4096);
 checkerr(err);
 err=snd_pcm_sw_params (playback, sw_params);
 checkerr(err);
}

void play_chunk()
{

}

int load_file(char *fn,buffer *buff)
{
 FILE *f=fopen(fn,"rb");
 if (f==NULL)
   return 0;
 fseek(f,0,SEEK_END);
 buff->length=ftell(f);
 fseek(f,0,SEEK_SET);
 buff->start=malloc(buff->length*sizeof(unsigned char));
 fread(buff->start,1,buff->length,f);
 fclose(f);
 return 1;
}